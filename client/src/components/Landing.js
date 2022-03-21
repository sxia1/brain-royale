import React from 'react';
import ReactDOM from 'react-dom';

import Container from '@mui/material/Container';
import Grid from '@mui/material/Grid';
import Box from '@mui/material/Box';
import Stack from '@mui/material/Stack';

import Typography from '@mui/material/Typography';

import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';

import { Outlet, Link } from "react-router-dom";

import {
	useParams,
	useNavigate,
	useLocation,
} from "react-router-dom";


function GamePlayModeButtons(prop) {
    const [value, setValue] = React.useState();

	let navigate = useNavigate();
	let location = useLocation();
	let params = useParams();


    const handleChange = (event) => {
        console.log(event.target.value);
        setValue(event.target.value);
    };


    return (
        <Stack direction="row" 
           sx={{ justifyContent: 'center', my: 2 }} > 

            <Button variant="contained" sx={{ m: 1 }}
				onClick={() => {
				navigate("/tutorial"); }} >
				Tutorial
			</Button>

            <Button variant="contained" sx={{ m: 1 }} 
				onClick={() => {
				navigate("/join"); }} >
				Join Game
			</Button>

            <TextField id="outlined-basic" variant="outlined" size="small" sx={{ m: 1 }} 
                value={value}
                onChange={handleChange}
                label="Private Party" />
        </Stack>
    );

}



function Landing() {

    return (

        <Grid sx={{ justifyContent: 'center', alignItems: 'center',
            m: 5
            }}>
            <Box>
            </Box>
            <GamePlayModeButtons />
        </Grid>
    );
}

export default Landing; 
