import * as React from 'react';
import ReactDOM from 'react-dom';

import Box from '@mui/material/Box';

import { red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey } from '@mui/material/colors';

import parse from 'html-react-parser';
import twemoji from 'twemoji';
// var emoji = require('emoji.json/emoji.json')
var emoji = require('emoji.json/emoji-compact.json')

const random = (items) => items[Math.floor(Math.random() * items.length)];

const material_colors = [red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey];

function shuffle(array) {
  for (let i = array.length - 1; i > 0; i--) {
    let j = Math.floor(Math.random() * (i + 1));
    [array[i], array[j]] = [array[j], array[i]];
  }
}

function getEmoji() {
    let twimg = twemoji.parse(random(emoji));
    twimg = parse(twimg);
    twimg = Array.isArray(twimg) ? twimg[0] : twimg;
    return (twimg.props && twimg.props.src) ? twimg.props.src : getEmoji() ;
}

function Player(props) {
    const [color, setColor] = React.useState(random(material_colors)); 
    const [shade, setShade] = React.useState(random([0, 1, 2])); 
    const [colors, setColors] = React.useState([]); 
    const [icon, setIcon] = React.useState(getEmoji()); 

    function updatePlayerShades() {
        let shuffled  = [Object.values(color)[shade], Object.values(color)[shade + 1]]; 
        // player_shades.push(player_color[random([50,100,200,300,400].filter(color => !player_shades.includes(color)))]);
        shuffle(shuffled);
        setColors(shuffled);
    }

    React.useEffect(() => {updatePlayerShades()}, [shade]);

    // opacity: `${Math.random() * (.25) + .75}`, 
    return (
        <Box sx={{ background: `linear-gradient(to right bottom, ${colors.slice(0,2).join(',')})`, 
            width: 50, height: 50, p: 1.5, m: 1/3, borderRadius: 28 }} 
            onMouseEnter={() => setShade(shade + 1)}
            onMouseLeave={() => setShade(shade - 1)} >
            <img src={icon} />
        </Box>
    );
}



export default Player; 
