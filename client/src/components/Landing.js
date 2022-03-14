import React from 'react';
import ReactDOM from 'react-dom';

import Container from '@mui/material/Container';
import Grid from '@mui/material/Grid';
import Box from '@mui/material/Box';
import Stack from '@mui/material/Stack';

import Typography from '@mui/material/Typography';

import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';



function GamePlayModeButtons(prop) {
    return (
        <Stack direction="row" 
           sx={{ justifyContent: 'center', my: 2 }} > 
            <Button variant="contained" sx={{ m: 1 }} >Tutorial</Button>
            <Button variant="contained" sx={{ m: 1 }} >Join Game</Button>
            <TextField id="outlined-basic" variant="outlined" size="small" sx={{ m: 1 }} 
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
                <Typography variant="h2" component="div" sx={{ textAlign: 'center', my: 2 }}>
                Brain Royale
                </Typography>
            </Box>
            <GamePlayModeButtons />
        </Grid>
    );
}

export default Landing; 
