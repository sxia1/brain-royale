import React from 'react';
import ReactDOM from 'react-dom';

import Container from '@mui/material/Container';
import Grid from '@mui/material/Grid';
import Box from '@mui/material/Box';

import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';



function GamePlayModeButtons(prop) {
    return (
        <Box container sx={{ justifyContent: 'space-around', alignContent: 'flex-start' }} >
            <Button variant="contained" sx={{ m: 1 }} >Tutorial</Button>
            <Button variant="contained" sx={{ m: 1 }} >Join Game</Button>
            <Button variant="contained" sx={{ m: 1 }} >Private Party</Button>
            <TextField id="outlined-basic" variant="outlined" size="small" sx={{ m: 1 }} 
                label="Private Party" />
        </Box>
    );

}


function Landing() {

    return (

        <Grid container sx={{ justifyContent: 'space-around', alignContent: 'flex-start', 
            width: '100%' }}>
            <GamePlayModeButtons />
        </Grid>
    );
}

export default Landing; 
