import React from 'react';
import ReactDOM from 'react-dom';
import Container from '@mui/material/Container';
import Grid from '@mui/material/Grid';
import Box from '@mui/material/Box';
import Skeleton from '@mui/material/Skeleton';

function Player(){
    return (
        <Skeleton variant="circular" sx={{ m: 1/3 }} 
            width={40} height={40} />
    );
}

function Game() {
    return (
        <Container>
            <Grid container>
                <Box sx={{ display: 'flex', flexWrap: 'wrap', maxWidth: 250 }}>
                    {Array.from(new Array(55)).map((item, index) => (<Player/>))}
                </Box>
                <Box sx={{ p: 1 }} >
                    <Skeleton variant="rectangular" animation="wave" sx={{ bgcolor: '#cfd8dc' }} 
                        height={500} width={600}/>
                </Box>
                <Box sx={{ p: 1 }} >
                    <Skeleton variant="rectangular" animation="wave" sx={{ bgcolor: 'gray.100' }} 
                        height={500} width={250}/>
                </Box>
            </Grid>
        </Container>
    );
}

export default Game; 
