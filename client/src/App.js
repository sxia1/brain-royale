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

    let game_id = null;
    if (location['pathname'].includes('join')) {
        game_id = location['pathname'].split('/');
        console.log(game_id);
    }

	return (
    <Container maxWidth={false} sx={{ mt: 2, mb: 10, mx: 0 }}>

        <Typography variant={ location['pathname'] == "/" ? "h2" : "h4" } component="div" sx={{ textAlign: 'center', my: 3 }}
			onClick={() => {
			navigate("/"); }} >
			Brain Royale{ game_id && game_id.length > 2 ? ` ${game_id[2]}` : '' }
		</Typography>

        <Outlet />

    </Container>
	);
}

export default App;
