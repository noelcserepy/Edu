import React from "react";

const Navbar = ({ totalCounters }) => {
	return (
		<nav class="navbar navbar-expand-lg navbar-light bg-light">
			<a class="navbar-brand" href="#">
				Navbar{" "}
				<span className="badge rounded-pill bg-secondary">{totalCounters}</span>
			</a>
		</nav>
	);
};

export default Navbar;
