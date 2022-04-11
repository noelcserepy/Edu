import React, { useEffect, useState } from "react";
import { debounce } from "lodash";
import { auth, googleAuthProvider, firebaseApp } from "../lib/firebase";
import { signInWithPopup, signOut } from "firebase/auth";
import {
	doc,
	getDoc,
	getFirestore,
	setDoc,
	writeBatch,
} from "firebase/firestore";
import { useCallback, useContext } from "react";
import { UserContext } from "../lib/context";
import { useValidateUsername } from "../lib/useValidate";
import Loader from "../components/Loader";
import toast from "react-hot-toast";

export default function EnterPage({}) {
	const { user, username } = useContext(UserContext);
	console.log("env " + process.env.SALI);

	return (
		<main>
			{user ? (
				!username ? (
					<UsernameForm />
				) : (
					<SignOutButton />
				)
			) : (
				<SignInButton />
			)}
		</main>
	);
}

function SignInButton() {
	const signInWithGoogle = async () => {
		try {
			await signInWithPopup(auth, googleAuthProvider);
		} catch (ex) {
			console.log(ex);
		}
	};

	return (
		<button className="btn-google" onClick={signInWithGoogle}>
			<img src={"/google.png"} />
			Sign in with Google
		</button>
	);
}

const SignOutButton = () => {
	return <button onClick={() => signOut(auth)}>Sign Out</button>;
};

function UsernameForm() {
	const [formValue, setFormValue] = useState("");
	const [isValid, setIsValid] = useState(false);
	const [isFree, setIsFree] = useState(false);
	const [loading, setLoading] = useState(false);
	const [error, setError] = useState(null);

	const { user, username } = useContext(UserContext);

	const handleSubmit = async e => {
		e.preventDefault();

		if (isValid && isFree) {
			const userDoc = doc(getFirestore(firebaseApp), "users", user.uid);
			const usernameDoc = doc(
				getFirestore(firebaseApp),
				"usernames",
				formValue
			);

			const batch = writeBatch(getFirestore(firebaseApp));
			batch.set(userDoc, {
				username: formValue,
				photoURL: user.photoURL,
				displayName: user.displayName,
			});
			batch.set(usernameDoc, { uid: user.uid });
			await batch.commit();
		}
	};

	const handleChange = e => {
		const { value, error } = useValidateUsername(e.target.value);
		setFormValue(value.username);

		if (error) {
			setError(error.message);
			setIsValid(false);
		} else {
			setError(null);
			setIsValid(true);
		}
	};

	useEffect(() => {
		setLoading(true);
		checkUsername();
	}, [formValue]);

	const checkUsername = useCallback(
		debounce(async () => {
			if (formValue.length >= 3) {
				const ref = doc(getFirestore(firebaseApp), "usernames", formValue);
				const snap = await getDoc(ref);
				if (snap.exists()) {
					console.log("Document data:", docSnap.data());
					setIsFree(false);
					setError("Username is already taken :(");
				} else {
					console.log("No such document!");
					setIsFree(true);
				}
				setLoading(false);
			}
		}, 500),
		[]
	);

	return (
		<section>
			<h3>Choose Username</h3>
			<form onSubmit={handleSubmit}>
				<input
					name="username"
					placeholder="myname"
					value={formValue}
					onChange={handleChange}
				/>
				{error && <p>{error}</p>}
				<Loader show={loading} />

				<button type="submit" className="btn-green" disabled={!isValid}>
					Choose
				</button>
				<h3>Debug State</h3>
				<div>
					Username: {formValue}
					<br />
					Loading: {loading.toString()}
					<br />
					Username Valid: {isValid.toString()}
				</div>
			</form>
		</section>
	);
}
