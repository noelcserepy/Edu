import React, { useContext } from "react";
import Joi from "joi-browser";
import Input from "./input";
import Select from "./select";
import { Link } from "react-router-dom";
import FormDataContext from "../../utils/formDataContext";

const Form = () => {
	const fdc = useContext(FormDataContext);

	const validate = () => {
		const options = {
			abortEarly: false,
		};
		const { error } = Joi.validate(fdc.state.data, fdc.schema, options);
		if (!error) return null;

		const errors = {};
		error.details.map(d => (errors[d.path[0]] = d.message));
		return errors;
	};

	const validateProperty = ({ name, value }) => {
		const obj = { [name]: value };
		const schema = { [name]: fdc.schema[name] };
		const { error } = Joi.validate(obj, schema);
		return error ? error.details[0].message : null;
	};

	const handleSubmit = e => {
		e.preventDefault();

		const errors = validate();
		fdc.setState({ errors: errors || {} });
		if (errors) return;

		console.log("submitted");
	};

	const handleChange = ({ currentTarget: input }) => {
		const errors = { ...fdc.state.errors };
		const errorMessage = validateProperty(input);
		if (errorMessage) errors[input.name] = errorMessage;
		else delete errors[input.name];

		const data = { ...fdc.state.data };
		data[input.name] = input.value;
		fdc.setState({ data, errors });
	};

	const renderButton = (label, dest, onSave) => {
		return (
			<Link to={dest}>
				<button
					disabled={validate()}
					className="btn btn-primary mt-2"
					onClick={onSave}>
					{label}
				</button>
			</Link>
		);
	};

	const renderInput = (name, label, type = "text") => {
		const { data, errors } = fdc.state;

		return (
			<Input
				type={type}
				name={name}
				label={label}
				value={data[name]}
				error={errors[name]}
				onChange={handleChange}
			/>
		);
	};

	const renderSelect = (name, label, items) => {
		const { data, errors } = fdc.state;

		return (
			<Select
				name={name}
				label={label}
				items={items}
				value={data[name]}
				error={errors[name]}
				onChange={handleChange}
			/>
		);
	};
};

export default Form;
// class Form extends Component {
// 	state = { data: {}, errors: {} };

// 	validate = () => {
// 		const options = {
// 			abortEarly: false,
// 		};
// 		const { error } = Joi.validate(this.state.data, this.schema, options);
// 		if (!error) return null;

// 		const errors = {};
// 		error.details.map(d => (errors[d.path[0]] = d.message));
// 		return errors;
// 	};

// 	validateProperty = ({ name, value }) => {
// 		const obj = { [name]: value };
// 		const schema = { [name]: this.schema[name] };
// 		const { error } = Joi.validate(obj, schema);
// 		return error ? error.details[0].message : null;
// 	};

// 	handleSubmit = e => {
// 		e.preventDefault();

// 		const errors = this.validate();
// 		this.setState({ errors: errors || {} });
// 		if (errors) return;

// 		this.doSubmit();
// 	};

// 	handleChange = ({ currentTarget: input }) => {
// 		const errors = { ...this.state.errors };
// 		const errorMessage = this.validateProperty(input);
// 		if (errorMessage) errors[input.name] = errorMessage;
// 		else delete errors[input.name];

// 		const data = { ...this.state.data };
// 		data[input.name] = input.value;
// 		this.setState({ data, errors });
// 	};

// 	renderButton = (label, dest, onSave) => {
// 		return (
// 			<Link to={dest}>
// 				<button
// 					disabled={this.validate()}
// 					className="btn btn-primary mt-2"
// 					onClick={onSave}>
// 					{label}
// 				</button>
// 			</Link>
// 		);
// 	};

// 	renderInput = (name, label, type = "text") => {
// 		const { data, errors } = this.state;

// 		return (
// 			<Input
// 				type={type}
// 				name={name}
// 				label={label}
// 				value={data[name]}
// 				error={errors[name]}
// 				onChange={this.handleChange}
// 			/>
// 		);
// 	};

// 	renderSelect = (name, label, items) => {
// 		const { data, errors } = this.state;

// 		return (
// 			<Select
// 				name={name}
// 				label={label}
// 				items={items}
// 				value={data[name]}
// 				error={errors[name]}
// 				onChange={this.handleChange}
// 			/>
// 		);
// 	};
// }

// export default Form;
