import React, { Component } from "react";

const PostFeed = ({posts, admin}) => {
	return posts ? posts.map(post => <PostItem post={post} key={post.slug} admin={admin} />):;
};

export default PostFeed;

function PostItem({post, admin = false}){

}
