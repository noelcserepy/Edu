import React, { Component } from "react";
import { Link, NavLink } from "react-router-dom";

const Navbar = () => {
	return (
		<nav className="navbar navbar-expand-lg navbar-light bg-light">
			<div className="navbar-nav p-2">
				<NavLink to="/" className="navbar-brand">
					Vidly
				</NavLink>
				<NavLink to="/movies" className="nav-item nav-link">
					Movies
				</NavLink>
				<NavLink to="/customers" className="nav-item nav-link">
					Customers
				</NavLink>
				<NavLink to="/rentals" className="nav-item nav-link">
					Rentals
				</NavLink>
			</div>
		</nav>
	);
};

export default Navbar;
