import React, { useEffect, useState } from "react";
import Form from "./common/form";
import Joi from "joi-browser";
import { getGenres } from "../services/fakeGenreService";
import { saveMovie } from "../services/fakeMovieService";
import { useParams } from "react-router-dom";

const MovieForm = props => {
	const [state, setState] = useState();
	const { slug } = useParams();

	useEffect(() => {
		setState({
			data: {
				title: "",
				genreId: "",
				stock: 0,
				rate: 0,
			},
			genres: getGenres(),
			errors: {},
		});

		if (slug === "new") return;
	}, [state]);

	const schema = {
		title: Joi.string().required().label("Title"),
		genreId: Joi.string().required().label("Genre"),
		stock: Joi.number().integer().min(0).max(100).label("Number in Stock"),
		rate: Joi.number().min(0).max(10).label("Rate"),
	};

	return (
		<div>
			<h1>Movie Form</h1>
			<form onSubmit={() => saveMovie(state.data)}>
				{Form.renderInput("title", "Title")}
				{Form.renderSelect("genre", "Genre", state.genres)}
				{Form.renderInput("stock", "Stock")}
				{Form.renderInput("rate", "Rate")}
				{Form.renderButton("Save", "../movies")}
			</form>
		</div>
	);
};

export default MovieForm;

// import React from "react";
// import Form from "./common/form";
// import Joi from "joi-browser";
// import { getGenres } from "../services/fakeGenreService";
// import { saveMovie } from "../services/fakeMovieService";
// import { useMatch } from "react-router-dom";

// class MovieForm extends Form {
// 	state = {
// 		data: {
// 			title: "",
// 			genreId: "",
// 			stock: 0,
// 			rate: 0,
// 		},
// 		genres: [],
// 		errors: {},
// 	};

// 	componentDidMount() {
// 		const genres = getGenres();
// 		this.state.genres = genres;

// 		const match = useMatch();
// 		const movieId = match.params.id;
// 		if (movieId === "new") return;
// 	}

// 	schema = {
// 		title: Joi.string().required().label("Title"),
// 		genreId: Joi.string().required().label("Genre"),
// 		stock: Joi.number().integer().min(0).max(100).label("Number in Stock"),
// 		rate: Joi.number().min(0).max(10).label("Rate"),
// 	};

// 	doSubmit = () => {
// 		console.log("submitted");
// 	};

// 	handleSave = () => {
// 		saveMovie(this.state.data);
// 	};

// 	render() {
// 		return (
// 			<div>
// 				<h1>Movie Form</h1>
// 				<form onSubmit={this.handleSubmit}>
// 					{this.renderInput("title", "Title")}
// 					{this.renderSelect("genre", "Genre", this.state.genres)}
// 					{this.renderInput("stock", "Stock")}
// 					{this.renderInput("rate", "Rate")}
// 					{this.renderButton("Save", "../movies", this.handlesave)}
// 				</form>
// 			</div>
// 		);
// 	}
// }

// export default MovieForm;
