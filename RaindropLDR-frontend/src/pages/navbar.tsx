import '../assets/navbar-fixed.css'
import '../assets/bootstrap.bundle.min.js'
import { BrowserRouter, Routes, Route, Outlet, Link } from "react-router-dom";
import App from '../App.jsx'
import About from './about.tsx'
import Details from './details.tsx'
import NoFile from './nofile.tsx'

export function Routing() {
    return (
        <BrowserRouter>
            <Routes>
                <Route path="/" element={<App />}>
                    <Route path="/details" element={<Details />} />
                    <Route path="/about" element={<About />} />
                    <Route path="*" element={<NoFile />} />
                </Route>
            </Routes>
        </BrowserRouter>
    );
}

export default function Navbar() {
    return (
        <>
            <nav>
                <ul>
                    <li>
                        <Link to="/">Home</Link>
                    </li>
                    <li>
                        <Link to="/about">About</Link>
                    </li>
                    <li>
                        <Link to="/dashboard">Dashboard</Link>
                    </li>
                    <li>
                        <Link to="/nothing-here">Nothing Here</Link>
                    </li>
                </ul>
            </nav>
            < Outlet />
        </>
    )
}