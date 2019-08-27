function generateChart(divId, jsonData){
    chart = c3.generate({
        bindTo: '${divId}',
        data: {
            json: jsonData,
            keys: {
                x: 'time', // it's possible to specify 'x' when category axis
                value: ['north', 'east', 'up'],
            }
        },
        axis: {
            x: {
//                type: 'category'
            }
        }
    });
}