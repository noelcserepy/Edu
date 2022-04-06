import { BrowserRouter, Route, Routes, Navigate } from "react-router-dom";
import Customers from "./components/customers";
import Movies from "./components/movies";
import NotFound from "./components/notFound";
import Rentals from "./components/Rentals";
import MovieForm from "./components/movieForm";
import Layout from "./components/layout";
import LoginForm from "./components/loginForm";
import "./App.css";
import RegisterForm from "./components/registerForm";

function App() {
	return (
		<BrowserRouter>
			<Routes>
				<Route path="/" element={<Layout />}>
					<Route path="/" element={<Navigate to="/movies" />} />
					<Route path="login" element={<LoginForm />} />
					<Route path="register" element={<RegisterForm />} />
					<Route path="movies" element={<Movies />} />
					<Route path="movies/:movieId" element={<MovieForm />} />
					<Route path="customers" element={<Customers />} />
					<Route path="rentals" element={<Rentals />} />
					<Route path="*" element={<NotFound />} />
				</Route>
			</Routes>
		</BrowserRouter>
	);
}

export default App;
