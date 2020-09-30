const fs = require('fs')
const path = require('path')

function readDir(dir) {
    fs.promises.readdir(dir)
        .then(files => files.forEach(f => {
            const file = path.resolve(dir, f)
            if (fs.statSync(file).isDirectory()) {
                readDir(file)
            } else if (!file.endsWith('.d.ts')) {
                fs.unlink(file, () => { })
            }
        }))
}

readDir(path.resolve(__dirname, 'interface'))
