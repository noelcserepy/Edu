import React, { Component, useEffect, useState } from "react";
import Joi from "joi-browser";
import Form from "./common/form";
import FormDataContext from "../utils/formDataContext";

const RegisterForm = () => {
	const [state, setState] = useState();

	useEffect(() => {
		state = {
			data: {
				username: "",
				password: "",
				name: "",
			},
			errors: {},
		};
	}, [state]);

	const schema = {
		username: Joi.string()
			.email({ minDomainSegments: 2 })
			.required()
			.label("Username"),
		password: Joi.string().min(5).required().label("Password"),
		name: Joi.string().required().label("Name"),
	};

	const formData = { state, schema, setState };

	return (
		<div>
			<FormDataContext value={formData}>
				<h1>Register</h1>
				<form onSubmit={Form.handleSubmit}>
					{Form.renderInput("username", "Username")}
					{Form.renderInput("password", "Password", "password")}
					{Form.renderInput("name", "Name")}
					{Form.renderButton("Register")}
				</form>
			</FormDataContext>
		</div>
	);
};

export default RegisterForm;
