import { BrowserRouter, Route, Routes, Navigate } from "react-router-dom";
import "./App.css";
import Customers from "./components/customers";
import Movies from "./components/movies";
import NotFound from "./components/notFound";
import Rentals from "./components/Rentals";
import MovieForm from "./components/movieForm";
import Layout from "./components/layout";

function App() {
	return (
		<BrowserRouter>
			<Routes>
				<Route path="/" element={<Layout />}>
					<Route path="/" element={<Navigate to="/movies" />} />
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
