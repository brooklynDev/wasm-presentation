// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

import {dotnet} from './dotnet.js'

const {getAssemblyExports, getConfig} = await dotnet
    .withDiagnosticTracing(false)
    .withApplicationArgumentsFromQuery()
    .create();



const config = getConfig();
const exports = await getAssemblyExports(config.mainAssemblyName);

await dotnet.run();

const qst = selector => document.querySelector(selector).value;

document.querySelector('.btn-dark').onclick = () => {
    const to = qst('#to');
    const cc = qst('#cc');
    const subject = qst('#subject');
    const body = qst('#body');
    const downloadMsg = exports.MyClass.DownloadMsg;
    const msg = downloadMsg(subject, to, cc, body);
    let blob = new Blob([msg], {type: "application/octet-stream"});

    let url = URL.createObjectURL(blob);

    let downloadLink = document.createElement("a");
    downloadLink.href = url;
    downloadLink.download = "foo.msg";
    document.body.appendChild(downloadLink);

    downloadLink.click();
    document.body.removeChild(downloadLink);
}
