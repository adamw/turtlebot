var turtlebot = {
    penIsDown: false,

    sparkConfigured: function() {
        return typeof spark != 'undefined';
    },

    execute: function (command, args) {
        console.log('execute ' + command + ' ' + args);
        if (this.sparkConfigured()) {
            $.post('https://api.spark.io/v1/devices/' + spark.deviceId + '/' + command, {
                access_token: spark.accessToken,
                args: args
            });
        } else {
            console.error('Spark not configured. See spark.js.template for details')
        }
    },

    forward: function (distance) {
        console.log('forward');
        this.execute('move', distance);
    },

    backward: function (distance) {
        console.log('backward');
        this.execute('move', -distance);
    },

    left: function (angle) {
        console.log('left');
        this.execute('rotate', -angle);
    },

    right: function (angle) {
        console.log('right');
        this.execute('rotate', angle);
    },

    togglePen: function () {
        this.penIsDown ? this.penUp() : this.penDown();
    },

    penUp: function () {
        console.log('pen up');
        this.execute('penmove', 1);
        this.penIsDown = false;
    },

    penDown: function () {
        console.log('pen down');
        this.execute('penmove', -1);
        this.penIsDown = true;
    }
};

function numericFieldValue(fieldId) {
    var textValue = $('#' + fieldId).val();
    return parseInt(textValue);
}

$('#forward').click(function () {
    var distance = numericFieldValue('forwardDistance');
    turtlebot.forward(distance);
});

$('#backward').click(function () {
    var distance = numericFieldValue('backwardDistance');
    turtlebot.backward(distance);
});

$('#left').click(function () {
    var angle = numericFieldValue('leftAngle');
    turtlebot.left(angle);
});

$('#right').click(function () {
    var angle = numericFieldValue('rightAngle');
    turtlebot.right(angle);
});

$('#pen').click(function () {
    turtlebot.togglePen();
});

$(function () {
    if (!turtlebot.sparkConfigured()) {
        $('#sparkNotConfiguredMessage').show();
    }
});
