import { Outlet, Link } from "react-router-dom";
import Container from '@mui/material/Container';
import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';

import {
	useParams,
	useNavigate,
	useLocation,
} from "react-router-dom";

import './socket';

import Landing from './components/Landing';
import Game from './components/Game';




function App() {

	let navigate = useNavigate();
	let location = useLocation();
	let params = useParams();

	return (
    <Container maxWidth={false} sx={{ mt: 2, mb: 10, mx: 0 }}>

        <Typography variant="h2" component="div" sx={{ textAlign: 'center', my: 3 }}
			onClick={() => {
			navigate("/"); }} >
			Brain Royale
		</Typography>

        <Outlet />

    </Container>
	);
}

export default App;
