import axiosApi from './AxiosApi.js'


const apiList = {
  page: {
    method: 'POST',
    url: `/enc/enc/page`,
  
  },

//---------------------------------------------------------------------------------------
  update: {
    method: 'PUT',
    url: `/enc/enc`
    //url:'/ecn/ecnupdate'                       //修改
  },


//----------------------------------------------------------------------------------------

  save: {
    method: 'POST',
    url: `/enc/enc`
     //url:'/ecn/ecnadd'               //新增
  },


  //=====================================================================================
  delete: {
    method: 'DELETE',
    url: `/enc/enc`
    //url: `/ecn/ecndelect`                            //删除
  },

  //=====================================================================================
  preview: {
    method: 'POST',
    url: `/enc/enc/preview`
  },
  export: {
    method: 'POST',
    url: `/enc/enc/export`
  },
  import: {
    method: 'POST',
    url: `/enc/enc/import`
    //url:'/ecn/ecnadd'               //新增                                
  }
}






export default {
  page (data, custom = {}) {
    return axiosApi({
      ...apiList.page,
      data,
      custom
    })
  },
  save (data) {
    return axiosApi({
      ...apiList.save,
      data
    })
  },


//--------------------------------------------------------
  update (data) {
    return axiosApi({
      ...apiList.update,
      data
    })
  },

//---------------------------------------------------------


  delete (data) {
   
    return axiosApi({
      ...apiList.delete,
      data
    })
  },
  preview (data) {
    return axiosApi({
      ...apiList.preview,
      data
    })
  },
  export (data) {
    return axiosApi({
      ...apiList.export,
      responseType: "blob",
      data
    })
  },
  import (data) {
    return axiosApi({
      ...apiList.import,
      data
    })                          //新增
  }
}
