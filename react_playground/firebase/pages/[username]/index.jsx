import PostFeed from "../../components/PostFeed";
import UserProfile from "../../components/UserProfile";
import {
	getUserPosts,
	getUserWithUsername,
	postToJSON,
} from "../../lib/firebase";

export async function getServerSideProps({ query }) {
	const { username } = query;

	const userDoc = await getUserWithUsername(username);

	let user = null;
	let posts = [];

	if (userDoc) {
		user = userDoc.data();

		const postSnap = await getUserPosts(userDoc);
		postSnap.forEach(p => posts.push(postToJSON(p)));
	}

	return {
		props: {
			user,
			posts,
		},
	};
}

export default function User({ user, posts }) {
	return (
		<main>
			<h1>User</h1>
			<UserProfile user={user} />
			<PostFeed posts={posts} />
		</main>
	);
}
