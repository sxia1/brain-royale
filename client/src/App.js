import React from 'react';

import { Outlet, Link } from "react-router-dom";
import Container from '@mui/material/Container';
import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import { blue } from '@mui/material/colors';

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

    let header = {};
    if (location['pathname'] == "/") {
        header = {"typography": "h2", "align": "center"};
    }
    else {
        header = {"typography": "h4", "align": "left"};
    }

	return (
	<Container maxWidth={false} sx={{ mt: 2, mb: 10, mx: 0 }}>

        <Box sx={{ my: 3, px: 7, textAlign: header["align"] }}>
            <Typography variant={ header["typography"] } 
                className="transition duration-300" component="span" 
                sx={{ ":hover": { color: '#DD2E44' } }}
                onClick={() => { navigate("/"); }} >
                Brain Royale{ game_id && game_id.length > 2 ? ` ${game_id[2]}` : '' }
            </Typography>
        </Box>

		<Outlet />

	</Container>
	);
}

export default App;
