import React from 'react';
import ReactDOM from 'react-dom';
import { render } from "react-dom";
import './index.css';
import App from './App';
import LandingPage from './routes/LandingPage';
import GamePage from './routes/GamePage';
import ErrorPage from './routes/ErrorPage';
import reportWebVitals from './reportWebVitals';
// import 'bootstrap/dist/css/bootstrap.min.css';

import {
      BrowserRouter,
      Routes,
      Route,
} from "react-router-dom";


const rootElement = document.getElementById("root");
render(
    <BrowserRouter>
        <Routes>
            <Route path="/" element={<App />}>
                <Route index element={<GamePage/>} />
                <Route path="join" element={<GamePage />} >
                    <Route path=":code" element={<GamePage />} />
                </Route>
                <Route path="tutorial" element={<ErrorPage message="This is currently unimplemented. Come back soon!" />} />
                <Route path="scoreboard" element={<ErrorPage message="This is currently unimplemented. Come back soon!" />} />
				<Route path="*" element={<ErrorPage />} />
            </Route>
        </Routes>
    </BrowserRouter>,
    rootElement
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
