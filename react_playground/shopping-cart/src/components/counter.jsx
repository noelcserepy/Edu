import React, { Component } from "react";

class Counter extends Component {
	render() {
		return (
			<div className="container row row-cols-auto">
				<div className="col-1">
					<span className={this.getBadgeClasses()} style={{ minWidth: 55 }}>
						{this.formatCount()}
					</span>
				</div>
				<div className="col">
					<button
						onClick={() => this.props.onIncrement(this.props.counter)}
						className="btn btn-secondary btn-sm "
						style={{ minWidth: 30 }}
					>
						+
					</button>
					<button
						onClick={() => this.props.onDecrement(this.props.counter)}
						className="btn btn-secondary btn-sm m-2"
						style={{ minWidth: 30 }}
						disabled={this.props.counter.value < 1}
					>
						-
					</button>
					<button
						onClick={() => this.props.onDelete(this.props.counter.id)}
						className="btn btn-danger btn-sm "
						style={{ minWidth: 30 }}
					>
						x
					</button>
				</div>
			</div>
		);
	}

	getBadgeClasses() {
		let classes = "badge m-2 bg-";
		classes += this.props.counter.value === 0 ? "warning" : "primary";
		return classes;
	}

	formatCount() {
		const { value } = this.props.counter;
		return value === 0 ? "Zero" : value;
	}
}

export default Counter;
