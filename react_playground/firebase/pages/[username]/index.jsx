import PostFeed from "../../components/PostFeed";
import UserProfile from "../../components/UserProfile";

export default function User({ user, posts }) {
	return (
		<main>
			<h1>User</h1>
			<UserProfile user={user} />
			<PostFeed posts={posts} />
		</main>
	);
}
