import React, { Component } from "react";
import Like from "./common/like";

const MoviesTable = props => {
	const { movies, onLike, onDelete } = props;
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
				{movies.map(movie => (
					<tr key={movie._id}>
						<td>{movie.title}</td>
						<td>{movie.genre.name}</td>
						<td>{movie.numberInStock}</td>
						<td>{movie.dailyRentalRate}</td>
						<td>
							<Like onLike={() => onLike(movie)} liked={movie.liked} />
						</td>
						<td>
							<button
								onClick={() => onDelete(movie._id)}
								className="btn btn-danger"
								type="button">
								Delete
							</button>
						</td>
					</tr>
				))}
			</tbody>
		</table>
	);
};

export default MoviesTable;
