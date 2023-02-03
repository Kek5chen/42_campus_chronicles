import express, { Express, Request, Response } from 'express';
import dotenv from 'dotenv';
import { PrismaClient, User } from "@prisma/client";
import md5 from "md5"
import bodyParser from "body-parser"
import { RemoveLastDirectoryPartOf} from './functions';
import Logger from 'js-logger';
import { PrismaClientKnownRequestError, PrismaClientUnknownRequestError } from '@prisma/client/runtime';

dotenv.config();

const port = process.env.PORT

const app: Express = express()
const root = RemoveLastDirectoryPartOf(__dirname)
const prisma = new PrismaClient()

//remove "/build" from __dirname to create absolute path to project root


app.get('/', (req: Request, res: Response) => {
  res.send('server root page');
});

//retrieve list of users data
app.get("/api/users", async (req, res, next) => {
    const Users = await prisma.user.findMany().catch(e  => {Logger.error(`error while trying to list all users`); return `error while trying to list all users`})
	res.json(Users)
});

//retrieve user by id
app.get("/api/user/:id", async (req, res, next) => {
	const userId = req.params.id
	const Users = await prisma.user.findMany({
		where: {id: parseInt(userId)}
	}).catch(e => {Logger.error(`error while trying to get user id: ${userId}`); return `error while trying to get user id: ${userId}`})
	res.json(Users)
});
	

//add new user
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.post("/api/user/", async (req: Request, res: Response, next) => {
    var errors=[]
	if (!req?.body?.username){
        errors.push("No name specified");
    }

    if (!req?.body?.password){
        errors.push("No password specified");
    }
    if (!req?.body?.email){
        errors.push("No email specified");
    }
    if (errors.length){
        res.status(400).json({"error":errors.join(",")});
        return;
    }
		const newUser = await prisma.user.create({
			data: {
				username: req.body.username,
				email:	  req.body.email,
				password: md5(req.body.password)
			}
		}).catch(e => {
			if (e instanceof PrismaClientKnownRequestError)
				if (e.code === 'P2002') {
					Logger.error('Unique constraint violation, new entry "user" can not be created')
					return 'Unique database constraint violation'
				}
			else if (e instanceof PrismaClientUnknownRequestError){
				Logger.error('unknown error occured at user creation')
				return 'unknown error occured at user creation'
			}
			else {
				Logger.error('idk wtf happened this time, it is not working (audible head banging against wall noises)')
				return 'idk wtf happened this time, it is not working (audible head banging against wall noises)'
			}
		})
		res.json(newUser)
	
})

//update user information
app.patch("/api/user/:id", async (req: Request, res: Response, next) => {

	const user = await prisma.user.findUnique({
		where: {id: parseInt(req.params.id)}
	}).catch(e => console.log(e))
	if(user){
		const updatedUser = await prisma.user.update({
			where: {id: parseInt(req.params.id)},
			data: {
				username: req?.body?.username ? req.body.username : user?.username,
				email: req?.body?.email ? req.body.email : user?.email,
				password: req?.body?.password ? md5(req.body.password) : user?.password
			}
		}).catch(e => {
			if (e instanceof PrismaClientKnownRequestError)
				if (e.code === 'P2002') {
					Logger.error('Unique constraint violation, new entry "user" can not be created')
					return 'Unique database constraint violation'
				}
			else if (e instanceof PrismaClientUnknownRequestError){
				Logger.error('unknown error occured at user creation')
				return 'unknown error occured at user creation'
			}
			else {
				Logger.error('idk wtf happened this time, it is not working (audible head banging against wall noises)')
				return 'idk wtf happened this time, it is not working (audible head banging against wall noises)'
			}
		})
		res.json(updatedUser)
	}
	else
		res.json({"user": "user id does not exist"})
})

//delete user by id
app.delete("/api/user/:id", async (req, res, next) => {
	
	const user = await prisma.user.findUnique({
		where: {id: parseInt(req.params.id)}
	}).catch(e => {Logger.error(`error while trying to find user id: ${req.params.id}`); return `error while trying to find user id: ${req.params.id}`})
	if(user){
		const deletedUser = await prisma.user.delete({
			where: {id: parseInt(req.params.id)}
		}).catch(e => {Logger.error(`error while trying to delete user id: ${req.params.id}`); return `error while trying to delete user id: ${req.params.id}`})
		res.json({"user deleted": deletedUser})
	}
	else
		res.json({"user": `user id: ${req.params.id}, does not exist`})

})

app.use((req: Request, res: Response) =>{
	res.sendFile(root + '/views/404.html');
});

app.listen(port, () => {
  console.log(`⚡️[server]: Server is running at http://localhost:${port}`);
});
