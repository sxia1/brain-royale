import React from 'react';
import ReactDOM from 'react-dom';
import Button from '@mui/material/Button';
import Container from '@mui/material/Container';

function Landing() {

    return (
        <Container sx={{ width: '100%', justifyContent: 'center', alignContent: 'center' }}> 
            <Button variant="contained">Tutorial</Button>
            <Button variant="contained">Join Game</Button>
            <Button variant="contained">Private Party</Button>
        </Container>
    );
}

export default Landing; 
