import Head from "next/head";
import Image from "next/image";
import styles from "../styles/Home.module.css";
import toast from "react-hot-toast";
import { getHomePosts, postToJSON } from "../lib/firebase";
import { useState } from "react";
import PostFeed from "../components/PostFeed";
import Loader from "../components/Loader";
import { Timestamp } from "firebase/firestore";

const LIMIT = 1;

export async function getServerSideProps(context) {
	const posts = [];
	const postsSnap = await getHomePosts(LIMIT);
	postsSnap.forEach(p => posts.push(postToJSON(p)));

	return {
		props: { posts },
	};
}

export default function Home(props) {
	const [posts, setPosts] = useState(props.posts);
	const [loading, setLoading] = useState(false);
	const [postsEnd, setPostsEnd] = useState(false);

	const getMorePosts = async () => {
		setLoading(true);
		const last = posts[posts.length - 1];

		const cursor =
			typeof last.createdAt === "number"
				? Timestamp.fromMillis(last.createdAt)
				: last.createdAt;

		const newPosts = [];
		const newPostsSnap = await getHomePosts(LIMIT, cursor);
		newPostsSnap.forEach(p => newPosts.push(postToJSON(p)));

		setPosts(posts.concat(newPosts));
		setLoading(false);

		if (newPosts.length < LIMIT) {
			setPostsEnd(true);
		}
	};

	return (
		<div>
			<PostFeed posts={posts} />

			{!loading && !postsEnd && (
				<button onClick={getMorePosts}>Load more</button>
			)}

			<Loader show={loading} />

			{postsEnd && "You have reached the end!"}
		</div>
	);
}
