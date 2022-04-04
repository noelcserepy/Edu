import React, { Component } from "react";
import { useParams, Link } from "react-router-dom";

const MovieForm = ({ history }) => {
	const { movieId } = useParams();
	return (
		<div>
			<h1>Movie Detail - {movieId}</h1>
			<Link to="/movies">
				<button className="btn-sm btn-primary m-2">Save</button>
			</Link>
		</div>
	);
};

export default MovieForm;
