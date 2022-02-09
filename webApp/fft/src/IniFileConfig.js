
// class representing the .ini configuration file
export class IniFileConfig {
    centerFreq = 0; 
    sampleRate = 0;         // Fs 
    sampleInterval = 0;     // Ts

    constructor(centerFreq, sampleRate) {
        this.centerFreq = centerFreq;
        this.sampleRate = sampleRate;
        this.sampleInterval = 1/this.sampleRate;
    }

    // Returns the frequency range
    // If center is true, the range is [-Fs/2, Fs/2] (default)
    // If center is false, the range is [0, Fs]
    getFrequencyRange(numSamples, center = true) {

        var totalTime = this.sampleInterval*numSamples; // To
        var freqResolution = 1/totalTime;

        return Array.of(numSamples).map((_val, index) => {
            if (center) {
                return (index - numSamples/2)*freqResolution;
            } else {
                return index*freqResolution;
            }
        });

    }

    // Returns the normalized frequency range:
    // If center is true, the range is [-1/2, 1/2] (default)
    // If center is false, the range is [0, 1]
    getNormalizedFrequencyRange(numSamples, center = true) {
        
        var freqResolution = 1/numSamples;

        return Array.of(numSamples).map((_val, index) => {
            if (center) {
                return (index - numSamples/2)*freqResolution;
            } else {
                return index*freqResolution;
            }
        })
    }
}


// modified function from https://gist.github.com/anonymous/dad852cde5df545ed81f1bc334ea6f72
export function parseINIString(data){
    var regex = {
        section: /^\s*\[\s*([^\]]*)\s*\]\s*$/,
        param: /^\s*([^=]+?)\s*=\s*(.*?)\s*$/,
        comment: /^\s*;.*$/
    };
    var value = {};
    var lines = data.split(/[\r\n]+/);
    var section = null;
    lines.forEach(function(line){
        if(regex.comment.test(line)){
            return;
        }else if(regex.param.test(line)){
            var match = line.match(regex.param);
            if(section){
                value[section][match[1]] = match[2];
            }else{
                value[match[1]] = match[2];
            }
        }else if(regex.section.test(line)){
            var match = line.match(regex.section);
            value[match[1]] = {};
            section = match[1];
        }else if(line.length == 0 && section){
            section = null;
        };
    });
    return new IniFileConfig(parseFloat(value["Main"]["Center Frequency"]), parseFloat(value["Main"]["IQ Rate"]));
}
