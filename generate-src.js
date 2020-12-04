#!/usr/bin/env node

const { readdirSync, writeFileSync } = require('fs')
const { join } = require('path')

function *listDirectoryEntries(baseDir) {
    const entries = readdirSync(baseDir, {
        withFileTypes: true
    })

    for (const entry of entries) {
        if (entry.name.startsWith('.')) {
            continue
        }

        if (entry.isDirectory()) {
            yield *listDirectoryEntries(join(baseDir, entry.name))
        }

        if (!entry.isFile() || !entry.name.endsWith('.c')) {
            continue
        }

        yield join(baseDir, entry.name)
    }
}

function *generateSourcesList(baseDir) {
    const gen = listDirectoryEntries(baseDir)
    let isFirst = true

    for (const source of gen) {
        if (isFirst) {
            yield `SRCS = ${source}`
        } else {
            yield `SRCS += ${source}`
        }

        isFirst = false
    }
}

function stringifyList(list) {
    return list.join('\n') + '\n'
}

function outputList(list) {
    writeFileSync(join(__dirname, 'src.mk'), list)
}

function app() {
    const list = [...generateSourcesList('.')]
    const stringifiedList = stringifyList(list)

    outputList(stringifiedList)

    console.log('Generated src.mk file')
}

app()
