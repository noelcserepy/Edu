import Head from "next/head";
import Image from "next/image";
import styles from "../styles/Home.module.css";
import toast from "react-hot-toast";

export default function Home() {
	return (
		<div>
			<button onClick={() => toast.success("hello toast :D")}>Toast</button>
		</div>
	);
}
