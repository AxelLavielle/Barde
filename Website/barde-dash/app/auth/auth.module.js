/**
 * APLT
 * < arnaud perrault />
 * barde-dash - Created on 16/03/2017
 */

var currModule = {
    Name: "auth"
};

angular.module(currModule.Name, [
    currModule.Name + '.routes',
    currModule.Name + '.services',
    currModule.Name + '.controllers',
    //currModule.Name + '.directives'
]);

angular.module(currModule.Name).constant("CstAuth", {
    name: currModule.Name
});

angular.module(currModule.Name + '').run(
    ['CstAuth',
        function (Cst) {

            console.info(">>> " + Cst.name)
            console.info(Cst)
            console.info("<<< module initialized !")


        }]);

