import createApplication from './web/index';
import { IncomingMessage, ServerResponse, createServer } from 'http';

const app = createApplication();
app.get('/test/:g/:id', console.log);

