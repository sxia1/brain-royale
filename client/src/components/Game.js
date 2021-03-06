import * as React from 'react';
import ReactDOM from 'react-dom';

import {useState, useEffect} from "react";

import Container from '@mui/material/Container';
import Grid from '@mui/material/Grid';
import Box from '@mui/material/Box';

import { red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey } from '@mui/material/colors';

import Puzzle from './Puzzle';
import Player from './Player';

import {
	useParams,
	useNavigate,
	useLocation,
} from "react-router-dom";



class Game extends React.Component {

    constructor(props){
        super(props);
	const SOCKET_URL = 'ws://localhost:8080';
	const socket = new WebSocket(SOCKET_URL);

	socket.addEventListener('message', function (event) {
		console.log('Message from server ', JSON.parse(event.data));
	});

        this.state = {
            ws: socket,
            numPlayers: 0
        };
    }

    componentDidMount(){
        this.state.ws.onopen = () =>{
            this.joinLobby();
        }
		this.state.ws.onmessage = (e) => {
	    this.getData(e);
	}
 
    }

    joinLobby = () => {
        var request = {
            "type": "joinLobby",
            "data": 1
        };
        this.state.ws.send(JSON.stringify(request));
    }

    getData = (e) => {
        var msg = JSON.parse(e.data);
	console.log(e);
        if (msg.success){
            this.setState({numPlayers: msg.numUsers});
        }
    }

    render() {
        // 99 - 1 = 98 / 2 = 49 
        //let numPlayers = (33 - 1)/2;

        return (
            <Grid container sx={{ justifyContent: 'space-around', alignContent: 'flex-start', 
                width: '100%' }}>

                <Box sx={{ width: 1/5 }}>
                    <Box sx={{ height: 90 }} />

                    <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'space-evenly' }}>
                        {Array.from(new Array(this.state.numPlayers)).map((item, index) => (<Player />))}
                    </Box>
                </Box>

                <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'center', alignContent: 'center' }}>
                    <Puzzle websocket={this.state.ws}/>
                </Box>

                <Box sx={{ width: 1/5 }}>
                    <Box sx={{ height: 90 }} />

                    <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'space-evenly' }}>
                        {Array.from(new Array(this.state.numPlayers)).map((item, index) => (<Player />))}
                    </Box>
                </Box>

            </Grid>
        );
    };
}

export default Game; 
