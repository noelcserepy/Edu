import React, { Component } from "react";
import { Outlet } from "react-router-dom";
import Navbar from "./common/navbar";

const Layout = () => {
	return (
		<div>
			<Navbar />
			<div className="container">
				<Outlet />
			</div>
		</div>
	);
};

export default Layout;
