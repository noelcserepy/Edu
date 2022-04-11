import React, { Component, useEffect, useState } from "react";
import Joi from "joi-browser";
import Form from "./common/form";
import FormDataContext from "../utils/formDataContext";

const LoginForm = () => {
	const [state, setState] = useState();

	useEffect(() => {
		state = {
			data: {
				username: "",
				password: "",
			},
			errors: {},
		};
	}, [state]);

	const schema = {
		username: Joi.string().required().label("Username"),
		password: Joi.string().required().label("Password"),
	};

	const formData = { state, schema, setState };

	return (
		<div>
			<FormDataContext value={formData}>
				<h1>Login</h1>
				<form onSubmit={Form.handleSubmit}>
					{Form.renderInput("username", "Username")}
					{Form.renderInput("password", "Password", "password")}
					{Form.renderButton("Login")}
				</form>
			</FormDataContext>
		</div>
	);
};

export default LoginForm;
