import React, { Component } from "react";
import Counter from "./counter";

class Counters extends Component {
	render() {
		const { onReset, counters, onDelete, onIncrement, onDecrement } =
			this.props;
		return (
			<div className="col">
				<div className="row">
					<div className="col">
						<button onClick={onReset} className="btn btn-primary btn-sm m2">
							Reset
						</button>
					</div>
				</div>
				<div className="row">
					{counters.map((counter) => (
						<Counter
							key={counter.id}
							onDelete={onDelete}
							onIncrement={onIncrement}
							onDecrement={onDecrement}
							counter={counter}
						/>
					))}
				</div>
			</div>
		);
	}
}

export default Counters;
