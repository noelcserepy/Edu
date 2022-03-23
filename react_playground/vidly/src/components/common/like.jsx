import React from "react";
import { faHeart } from "@fortawesome/free-regular-svg-icons";
import { faHeart as solidHeart } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";

const Like = (props) => {
	const { onLike, liked } = props;
	return (
		<span onClick={onLike}>
			<FontAwesomeIcon
				icon={liked ? solidHeart : faHeart}
				style={{ cursor: "pointer" }}
			/>
		</span>
	);
};

export default Like;
