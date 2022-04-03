import React, { Component } from "react";

const ListGroup = ({
	onItemSelect,
	items,
	valueProperty,
	textProperty,
	selectedItem,
}) => {
	return (
		<ul className="list-group">
			{items.map(item => (
				<li
					key={item[valueProperty]}
					className={
						item === selectedItem ? "list-group-item active" : "list-group-item"
					}
					onClick={() => onItemSelect(item)}
					style={{ cursor: "pointer" }}>
					{item[textProperty]}
				</li>
			))}
		</ul>
	);
};

ListGroup.defaultProps = {
	textProperty: "name",
	valueProperty: "_id",
};

export default ListGroup;
