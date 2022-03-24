import React, { Component } from "react";
import { getMovies } from "../services/fakeMovieService";
import { getGenres } from "../services/fakeGenreService";

import Like from "./common/like";
import Pagination from "./common/pagination";
import { paginate } from "../utils/paginate";
import ListGroup from "./common/listGroup";
import MoviesTable from "./moviesTable";

class Movies extends Component {
	state = {};

	constructor() {
		super();
		let movies = getMovies();
		movies = movies.map(m => {
			m.liked = false;
			return m;
		});

		const genres = [{ name: "All Genres" }, ...getGenres()];

		this.state = {
			movies,
			genres,
			selectedGenre: genres[0],
			pageSize: 4,
			currentPage: 1,
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

	render() {
		const {
			currentPage,
			pageSize,
			movies: allMovies,
			selectedGenre: selectedGenre,
			genres,
		} = this.state;

		const filtered =
			selectedGenre && selectedGenre._id
				? allMovies.filter(m => m.genre._id === selectedGenre._id)
				: allMovies;

		const movieCount = filtered.length;

		if (movieCount === 0) return <p>There are no movies in the database</p>;

		const movies = paginate(filtered, currentPage, pageSize);

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
					<p>Showing {movieCount} movies in the database.</p>
					<MoviesTable
						movies={movies}
						onLike={this.handleLike}
						onDelete={this.handleDelete}
					/>
					<Pagination
						onPageChange={this.handlePageChange}
						itemCount={movieCount}
						pageSize={pageSize}
						currentPage={currentPage}
					/>
				</div>
			</div>
		);
	}
}

export default Movies;
