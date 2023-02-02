import express, { Express, Request, Response } from 'express';
import dotenv from 'dotenv';
var db = require("./db.js")

//remove "/build" from __dirname to create absolute path to project root
function RemoveLastDirectoryPartOf(url: string)
{
    var ret = url.split('/');
    ret.pop();
    return( ret.join('/') );
}

dotenv.config();

const app: Express = express();
const port = process.env.PORT;
const root = RemoveLastDirectoryPartOf(__dirname)

app.get('/', (req: Request, res: Response) => {
  res.send('testServer');
});

app.get("/api/users", (req, res, next) => {
    var sql = "select * from user"
    var params: Array<any> = []
    db.all(sql, params, (err: Error, rows: any) => {
        if (err) {
          res.status(400).json({"error":err.message});
          return;
        }
        res.json({
            "message":"success",
            "data":rows
        })
      });
});

  app.use((req: Request, res: Response) =>{
		res.sendFile(root + '/views/404.html');
	});

app.listen(port, () => {
  console.log(`⚡️[server]: Server is running at http://localhost:${port}`);
});
