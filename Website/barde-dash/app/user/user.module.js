/**
 * APLT
 * < arnaud perrault />
 * barde-dash - Created on 13/03/2017
 */

var currModule = {
    Name: "user"
};

angular.module(currModule.Name, [
    currModule.Name + '.routes',
    currModule.Name + '.services',
    currModule.Name + '.controllers',
    //currModule.Name + '.directives'
]);

angular.module(currModule.Name).constant("CstUser", {
    name: currModule.Name
});

angular.module(currModule.Name + '').run(
    ['CstUser',
        function (Cst) {

            console.info(">>> " + Cst.name)
            console.info(Cst)
            console.info("<<< module initialized !")


        }]);

