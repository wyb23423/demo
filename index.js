const xml2js = require('xml2js');
const fs = require('fs');
const path = require('path');
const translate = require('google-translate-api');

async function write({ list: { items } }) {
    const writeStream = fs.createWriteStream(path.resolve(__dirname, 'constant.js'));

    await Promise.all(items.map(async ({ $, item }) => {
        if (!isNaN(parseInt(item[0].$.alias || item[0].$.value))) {
            return;
        }

        const value = await Promise.all(item.map(({ $: item$ }) => {
            const key = item$.alias || item$.value;

            return translate(key, { to: 'en' })
                .then(({ text }) => text.replace(/^\d/, w => 'A' + w).replace(/[^A-Za-z\d]+/g, '_').toUpperCase())
                .then(text => text || 'NONE')
                .then(text => `  ${text}: ${item$.key}, // ${key}\n`)
        }))

        const name = $.alias.replace(/[A-Z]/g, w => '_' + w).toUpperCase()
        writeStream.write(`// ${$.label}\nexport const ${name} = Object.freeze({\n${value.join('')}})\n\n`)
    }))

    writeStream.end();
}

const parser = new xml2js.Parser();
fs.promises.readFile(path.resolve(__dirname, 'java/category.xml'))
    .then(data => parser.parseStringPromise(data))
    .then(write)
    .then(() => console.log('---------------------end---------------------'))

