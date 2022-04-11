import { initializeApp, getApps, getApp } from "firebase/app";
import { getAuth, GoogleAuthProvider } from "firebase/auth";
import { getFirestore } from "firebase/firestore";
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
