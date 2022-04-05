import React from "react";

const Select = ({ name, label, error, items, ...rest }) => {
	return (
		<div className="form-group">
			<label htmlFor={name}>{label}</label>
			<select className="form-control" name={name} id={name} {...rest}>
				{items.map(i => (
					<option key={i._id}>{i.name}</option>
				))}
			</select>
			{error && <div className="alert alert-danger">{error}</div>}
		</div>
	);
};

export default Select;
