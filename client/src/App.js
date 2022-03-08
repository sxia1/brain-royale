//import logo from './logo.svg';
//import './App.css';

import Landing from './components/Landing';
import Game from './components/Game';
import Container from '@mui/material/Container';
import Box from '@mui/material/Box';

/*

      <Landing />
      <Box sx={{ height: 50}}/>

*/

function App() {
  return (
    <Container sx={{ mt: 4 }}>
      <Game />
    </Container>
  );
}

export default App;
