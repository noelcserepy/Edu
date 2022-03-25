import React from "react";
import _ from "lodash";
import PropTypes from "prop-types";

const Pagination = ({ itemCount, pageSize, currentPage, onPageChange }) => {
	let totalPages = Math.ceil(itemCount / pageSize);
	if (totalPages <= 1) return null;
	const pages = _.range(1, totalPages + 1);

	return (
		<nav>
			<ul className="pagination">
				{pages.map(page => (
					<li
						key={page}
						className={page === currentPage ? "page-item active" : "page-item"}
						style={{ cursor: "pointer" }}>
						<a onClick={() => onPageChange(page)} className="page-link">
							{page}
						</a>
					</li>
				))}
			</ul>
		</nav>
	);
};

Pagination.propTypes = {
	itemCount: PropTypes.number.isRequired,
	pageSize: PropTypes.number.isRequired,
	currentPage: PropTypes.number.isRequired,
	onPageChange: PropTypes.func.isRequired,
};

export default Pagination;
