import createApplication from './web/index';
import { IncomingMessage, ServerResponse } from 'http';

const app = createApplication().listen(8082);
app.all('/test/:id', (req: IncomingMessage, res: ServerResponse) => {
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    res.end('33333');
});
