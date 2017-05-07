/**
 * APLT
 * < arnaud perrault />
 * barde-backoffice - Created on 13/03/2017
 */

var currModule = {
    Name: "dashboard"
};

angular.module(currModule.Name, [
    currModule.Name + '.routes',
    currModule.Name + '.services',
    currModule.Name + '.controllers',
    //currModule.Name + '.directives'
]);

angular.module(currModule.Name).constant("CstDashboard", {
    name: currModule.Name
});

angular.module(currModule.Name + '').run(
    ['CstDashboard',
        function (Cst) {

            console.info(">>> " + Cst.name)
            console.info(Cst)
            console.info("<<< module initialized !")


        }]);

