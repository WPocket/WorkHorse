import express from "express";
import { Endpoint } from "./endpoint";
const app = express();
const PORT = 8080; // default port to listen
const EGAD_PORT = 3360;
const DB_INDEX = -1;
const EGAD = "http://10.16.40.201" + ":" + EGAD_PORT + "/";
const TABLE_NAME = "endpoints";

// get a post request on url /endpoint/add that will add a new endpoint
app.post("/endpoint/add", (req, res) => {
    const body = req.body;
    try{
        const endpoint: Endpoint = {
            ip: body.ip,
            name: body.name,
            port: body.port,
            cores: body.cores? body.cores : 0,
            frequency: body.frequency? body.frequency : 0,
            memory: body.memory? body.memory : 0,
            disk: body.disk? body.disk : 0,
            bandwidth: body.bandwidth? body.bandwidth : 0
        };
        // make an api post request to EGAD with the endpoint
        const url:RequestInfo = EGAD + "endpoint/add";
        fetch(url, {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(endpoint)
        });
        res.send(endpoint);
    }catch(e){
        // tslint:disable-next-line:no-console
        console.log("error encountered: " + e);
        res.statusCode = 400;
        const err = {
            message: "error encountered",
            error_message: e.message
        }
        res.send(JSON.stringify(err));
    }



});



// start the Express server
app.listen(PORT, () => {
  // tslint:disable-next-line:no-console
  console.log(`server started at http://localhost:${PORT}`);
});
