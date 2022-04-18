import { initializeApp, getApps, getApp } from "firebase/app";
import { getAuth, GoogleAuthProvider } from "firebase/auth";
import {
	getFirestore,
	collection,
	query,
	where,
	getDocs,
	limit,
	orderBy,
	collectionGroup,
	startAfter,
} from "firebase/firestore";
import { getStorage } from "firebase/storage";

const firebaseConfig = {
	apiKey: process.env.NEXT_PUBLIC_API_KEY,
	authDomain: process.env.NEXT_PUBLIC_AUTH_DOMAIN,
	projectId: process.env.NEXT_PUBLIC_PROJECT_ID,
	storageBucket: process.env.NEXT_PUBLIC_STORAGE_BUCKET,
	messagingSenderId: process.env.NEXT_PUBLIC_MESSAGING_SENDER_ID,
	appId: process.env.NEXT_PUBLIC_APP_ID,
};

function createFirebaseApp(config) {
	try {
		return getApp();
	} catch {
		return initializeApp(config);
	}
}

export const firebaseApp = createFirebaseApp(firebaseConfig);
export const auth = getAuth(firebaseApp);
export const googleAuthProvider = new GoogleAuthProvider();
export const firestore = getFirestore(firebaseApp);
export const storage = getStorage(firebaseApp);

/**
 * @param {string} username
 */

export async function getUserWithUsername(username) {
	const q = query(
		collection(firestore, "users"),
		where("username", "==", username),
		limit(1)
	);
	const snap = await getDocs(q);
	return snap.docs[0];
}

export async function getUserPosts(userDoc) {
	const postsRef = collection(firestore, userDoc.ref.path, "posts");

	const q = query(
		postsRef,
		where("published", "==", true),
		orderBy("createdAt", "desc"),
		limit(5)
	);

	const snap = await getDocs(q);
	const posts = [];
	snap.forEach(p => posts.push(postToJSON(p)));

	return posts;
}

export function postToJSON(doc) {
	const data = doc.data();
	const d = {
		...data,
		createdAt: data.createdAt.toMillis(),
		updatedAt: data.updatedAt.toMillis(),
	};

	return d;
}

export async function getHomePosts(lim, afterDoc = null) {
	const postsRef = collectionGroup(firestore, "posts");
	if (afterDoc) {
		const q = query(
			postsRef,
			where("published", "==", true),
			orderBy("createdAt", "desc"),
			startAfter(afterDoc),
			limit(lim)
		);
		const snap = await getDocs(q);
		return snap;
	}
	const q = query(
		postsRef,
		where("published", "==", true),
		orderBy("createdAt", "desc"),
		limit(lim)
	);
	const snap = await getDocs(q);
	return snap;
}
