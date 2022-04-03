import React, { Component } from "react";
import Like from "./common/like";
import Table from "./common/table";

class MoviesTable extends Component {
	columns = [
		{ path: "title", label: "Title" },
		{ path: "genre.name", label: "Genre" },
		{ path: "numberInStock", label: "Stock" },
		{ path: "dailyRentalRate", label: "Rate" },
		{
			key: "like",
			content: movie => (
				<Like onLike={() => this.props.onLike(movie)} liked={movie.liked} />
			),
		},
		{
			key: "delete",
			content: movie => (
				<button
					onClick={() => this.props.onDelete(movie._id)}
					className="btn btn-danger"
					type="button">
					Delete
				</button>
			),
		},
	];

	render() {
		const { movies, onLike, onDelete, sortColumn, onSort } = this.props;
		return (
			<Table
				columns={this.columns}
				sortColumn={sortColumn}
				data={movies}
				onSort={onSort}
			/>
		);
	}
}

export default MoviesTable;
