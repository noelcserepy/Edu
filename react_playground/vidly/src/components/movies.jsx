import React, { Component } from "react";
import { getMovies } from "../services/fakeMovieService";

import Like from "./common/like";

class Movies extends Component {
	state = {};

	constructor() {
		super();
		let movies = getMovies();
		movies = movies.map((m) => {
			m.liked = false;
			return m;
		});
		this.state = { movies };
	}

	handleDelete = (_id) => {
		console.log("clicked delete");
		this.setState({
			movies: this.state.movies.filter((movie) => movie._id !== _id),
		});
	};

	handleLike = (movie) => {
		const movies = [...this.state.movies];
		const index = movies.indexOf(movie);
		movies[index] = { ...movie };
		movies[index].liked = !movies[index].liked;
		this.setState({ movies });
	};

	makeMovieRow = (movie) => {
		return (
			<tr key={movie._id}>
				<td>{movie.title}</td>
				<td>{movie.genre.name}</td>
				<td>{movie.numberInStock}</td>
				<td>{movie.dailyRentalRate}</td>
				<td>
					<Like onLike={() => this.handleLike(movie)} liked={movie.liked} />
				</td>
				<td>
					<button
						onClick={() => this.handleDelete(movie._id)}
						className="btn btn-danger"
						type="button"
					>
						Delete
					</button>
				</td>
			</tr>
		);
	};

	renderTable() {
		return (
			<table className="table">
				<thead>
					<tr>
						<th scope="col">Title</th>
						<th scope="col">Genre</th>
						<th scope="col">Stock</th>
						<th scope="col">Rate</th>
						<th scope="col"></th>
						<th scope="col"></th>
					</tr>
				</thead>
				<tbody>
					{this.state.movies.map((movie) => this.makeMovieRow(movie))}
				</tbody>
			</table>
		);
	}

	renderText(movieCount) {
		return movieCount > 0 ? (
			<p>Showing {movieCount} movies in the database.</p>
		) : (
			<p>There are no movies in the database</p>
		);
	}

	render() {
		let movieCount = this.state.movies.length;
		return (
			<React.Fragment>
				{this.renderText(movieCount)}
				{movieCount > 0 && this.renderTable()}
			</React.Fragment>
		);
	}
}

export default Movies;
