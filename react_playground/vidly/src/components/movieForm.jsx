import React from "react";
import Form from "./common/form";
import Joi from "joi-browser";
import { getGenres } from "../services/fakeGenreService";
import { saveMovie } from "../services/fakeMovieService";
import { Link, Navigate } from "react-router-dom";

class MovieForm extends Form {
	state = {
		data: {
			title: "",
			genre: "",
			stock: 0,
			rate: 0,
		},
		errors: {},
		genres: [],
	};

	constructor() {
		super();
		let genres = getGenres();
		this.state.genres = genres;
	}

	schema = {
		title: Joi.string().required().label("Title"),
		genre: Joi.string().required().label("Genre"),
		stock: Joi.number().integer().min(0).max(100).label("Number in Stock"),
		rate: Joi.number().integer().min(0).max(10).label("Rate"),
	};

	doSubmit = () => {
		console.log("submitted");
	};

	handleSave = () => {
		saveMovie(this.state.data);
		<Navigate to="/movies" />;
		console.log("saved");
	};

	render() {
		return (
			<div>
				<h1>Movie Form</h1>
				<form onSubmit={this.handleSubmit}>
					{this.renderInput("title", "Title")}
					{this.renderSelect("genre", "Genre", this.state.genres)}
					{this.renderInput("stock", "Stock")}
					{this.renderInput("rate", "Rate")}
					{this.renderButton("Save", this.handleSave)}
				</form>
			</div>
		);
	}
}

export default MovieForm;
