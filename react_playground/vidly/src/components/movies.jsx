import React, { Component } from "react";
import { getMovies } from "../services/fakeMovieService";
import { getGenres } from "../services/fakeGenreService";

import Pagination from "./common/pagination";
import { paginate } from "../utils/paginate";
import ListGroup from "./common/listGroup";
import MoviesTable from "./moviesTable";
import _ from "lodash";
import { Link, Outlet } from "react-router-dom";

class Movies extends Component {
	state = {};

	constructor() {
		super();
		let movies = getMovies();
		movies = movies.map(m => {
			m.liked = false;
			return m;
		});

		const genres = [{ _id: "", name: "All Genres" }, ...getGenres()];

		this.state = {
			movies,
			genres,
			selectedGenre: genres[0],
			pageSize: 4,
			currentPage: 1,
			sortColumn: { path: "title", order: "asc" },
		};
	}

	handleDelete = _id => {
		console.log("clicked delete");
		this.setState({
			movies: this.state.movies.filter(movie => movie._id !== _id),
		});
	};

	handleLike = movie => {
		const movies = [...this.state.movies];
		const index = movies.indexOf(movie);
		movies[index] = { ...movie };
		movies[index].liked = !movies[index].liked;
		this.setState({ movies });
	};

	handlePageChange = page => {
		this.setState({ currentPage: page });
	};

	handleFilterChange = genre => {
		this.setState({ selectedGenre: genre, currentPage: 1 });
	};

	handleSort = sortColumn => {
		this.setState({ sortColumn });
	};

	getPageData = () => {
		const {
			movies: allMovies,
			currentPage,
			pageSize,
			selectedGenre,
			sortColumn,
		} = this.state;

		const filtered =
			selectedGenre && selectedGenre._id
				? allMovies.filter(m => m.genre._id === selectedGenre._id)
				: allMovies;

		const sorted = _.orderBy(filtered, [sortColumn.path], [sortColumn.order]);
		const movies = paginate(sorted, currentPage, pageSize);

		return { totalCount: filtered.length, data: movies };
	};

	render() {
		const {
			currentPage,
			pageSize,
			sortColumn,
			movies: allMovies,
			selectedGenre,
			genres,
		} = this.state;

		const { totalCount, data } = this.getPageData(allMovies);

		if (totalCount === 0) return <p>There are no movies in the database</p>;

		return (
			<div className="row">
				<div className="col-3">
					<ListGroup
						onItemSelect={this.handleFilterChange}
						items={genres}
						selectedItem={selectedGenre}
					/>
				</div>
				<div className="col">
					<Link to="new">
						<button className="btn btn-primary">New Movie</button>
					</Link>
					<p>Showing {totalCount} movies in the database.</p>
					<MoviesTable
						onSort={this.handleSort}
						movies={data}
						sortColumn={sortColumn}
						onLike={this.handleLike}
						onDelete={this.handleDelete}
					/>
					<Pagination
						onPageChange={this.handlePageChange}
						itemCount={totalCount}
						pageSize={pageSize}
						currentPage={currentPage}
					/>
				</div>
			</div>
		);
	}
}

export default Movies;
